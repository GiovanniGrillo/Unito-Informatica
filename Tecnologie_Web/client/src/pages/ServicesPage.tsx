// src/pages/ServicesPage.tsx
import React, { useState, useEffect } from 'react';
import ServiceCard from '../components/features/ServiceCard';
import ServiceFilter from '../components/features/ServiceFilter';
import { Service } from '../types/Service';

interface AppointmentFormData {
  serviceId: number;
  date: string;
  time: string;
  name: string;
  email: string;
  phone: string;
  notes: string;
}

const ServicesPage: React.FC = () => {
  // Stato per tenere traccia del servizio selezionato
  const [selectedService, setSelectedService] = useState<Service | null>(null);
  const [formData, setFormData] = useState<AppointmentFormData>({
    serviceId: 0,
    date: '',
    time: '',
    name: '',
    email: '',
    phone: '',
    notes: ''
  });
  const [bookingSuccess, setBookingSuccess] = useState<boolean>(false);
  const [bookingError, setBookingError] = useState<string | null>(null);
  
  // Stato per memorizzare i servizi caricati dal backend
  const [services, setServices] = useState<Service[]>([]);
  const [filteredServices, setFilteredServices] = useState<Service[]>([]);
  const [categories, setCategories] = useState<string[]>([]);
  const [selectedCategory, setSelectedCategory] = useState<string | null>(null);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);
  
  // Caricamento dei servizi dal backend
  useEffect(() => {
    const fetchServices = async () => {
      try {
        setLoading(true);
        const response = await fetch('http://localhost:8080/services');
        
        if (!response.ok) {
          throw new Error('Errore nel caricamento dei servizi');
        }
        
        const data = await response.json();
        
        // Mappiamo i dati del backend al formato richiesto dal frontend
        const mappedServices = data.map((service: any) => ({
          id: service.id,
          category: service.category,
          title: service.name,
          price: parseFloat(service.price),
          description: service.description,
          imageSrc: service.imageUrl || '/img/hair_styles/default.webp',
        }));
        
        setServices(mappedServices);
        setFilteredServices(mappedServices);
        
        // Estrai le categorie uniche dai servizi
        const uniqueCategories = [...new Set(mappedServices.map((service: Service) => service.category))].sort();
        setCategories(uniqueCategories as string[]);
        
        setError(null);
      } catch (err) {
        console.error('Errore nel caricamento dei servizi:', err);
        setError('Impossibile caricare i servizi. Riprova più tardi.');
        // Carica dati di fallback in caso di errore
        setServices([]);
        setFilteredServices([]);
      } finally {
        setLoading(false);
      }
    };
    
    fetchServices();
  }, []);

  // Filtra i servizi quando cambia la categoria selezionata
  useEffect(() => {
    if (selectedCategory) {
      const filtered = services.filter(service => service.category === selectedCategory);
      setFilteredServices(filtered);
    } else {
      setFilteredServices(services);
    }
  }, [selectedCategory, services]);
  
  const handleCategoryChange = (category: string | null) => {
    setSelectedCategory(category);
  };
  
  // Gestione della prenotazione
  const handleBookService = (serviceId: number) => {
    const service = services.find(s => s.id === serviceId);
    if (service) {
      setSelectedService(service);
      setFormData(prev => ({ ...prev, serviceId: serviceId }));
    }
  };

  // Gestione dei cambiamenti nel form
  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>) => {
    const { name, value } = e.target;
    setFormData(prev => ({ ...prev, [name]: value }));
  };

  // Invio del form di prenotazione
  const handleSubmitBooking = async (e: React.FormEvent) => {
    e.preventDefault();
    
    try {
      // Preparazione dei dati per l'invio al server
      const appointmentData = {
        ...formData,
        userId: 1, // In un'app reale, questo verrebbe dall'autenticazione
      };

      // Invio della richiesta POST al server
      const response = await fetch('http://localhost:8080/api/appointments', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(appointmentData),
      });

      if (!response.ok) {
        throw new Error('Errore nell\'invio della prenotazione');
      }

      // Gestione del successo
      setBookingSuccess(true);
      setBookingError(null);
      setSelectedService(null);
      setFormData({
        serviceId: 0,
        date: '',
        time: '',
        name: '',
        email: '',
        phone: '',
        notes: ''
      });

    } catch (error) {
      setBookingError('Si è verificato un errore durante l\'invio della prenotazione.');
      console.error('Errore:', error);
    }
  };

  return (
    <main>
      <section className="services-content-area">
        <div className="section" id="servizi">
          <h2>Servizi</h2>
          <p>
            Offriamo una gamma di servizi per la cura e lo styling dei capelli, con prodotti di alta qualità e tecniche avanzate.
          </p>
          
          {/* Componente di filtro */}
          {categories.length > 0 && (
            <ServiceFilter 
              categories={categories}
              selectedCategory={selectedCategory}
              onCategoryChange={handleCategoryChange}
            />
          )}
        </div>
      </section>
      
      {loading && (
        <div className="loading-message">
          <p>Caricamento dei servizi in corso...</p>
        </div>
      )}
      
      {error && (
        <div className="error-message">
          {error}
          <button onClick={() => setError(null)}>Chiudi</button>
        </div>
      )}
      
      {bookingSuccess && (
        <div className="success-message">
          Prenotazione effettuata con successo! Ti contatteremo presto per confermare.
          <button onClick={() => setBookingSuccess(false)}>Chiudi</button>
        </div>
      )}

      {bookingError && (
        <div className="error-message">
          {bookingError}
          <button onClick={() => setBookingError(null)}>Chiudi</button>
        </div>
      )}
      
      {selectedService && (
        <div className="booking-form-overlay">
          <div className="booking-form-container">
            <h3>Prenota {selectedService.title}</h3>
            <form onSubmit={handleSubmitBooking}>
              <div className="form-group">
                <label htmlFor="name">Nome e Cognome:</label>
                <input
                  type="text"
                  id="name"
                  name="name"
                  value={formData.name}
                  onChange={handleInputChange}
                  required
                />
              </div>
              
              <div className="form-group">
                <label htmlFor="email">Email:</label>
                <input
                  type="email"
                  id="email"
                  name="email"
                  value={formData.email}
                  onChange={handleInputChange}
                  required
                />
              </div>
              
              <div className="form-group">
                <label htmlFor="phone">Telefono:</label>
                <input
                  type="tel"
                  id="phone"
                  name="phone"
                  value={formData.phone}
                  onChange={handleInputChange}
                  required
                />
              </div>
              
              <div className="form-group">
                <label htmlFor="date">Data:</label>
                <input
                  type="date"
                  id="date"
                  name="date"
                  value={formData.date}
                  onChange={handleInputChange}
                  required
                />
              </div>
              
              <div className="form-group">
                <label htmlFor="time">Orario:</label>
                <input
                  type="time"
                  id="time"
                  name="time"
                  value={formData.time}
                  onChange={handleInputChange}
                  required
                />
              </div>
              
              <div className="form-group">
                <label htmlFor="notes">Note aggiuntive:</label>
                <textarea
                  id="notes"
                  name="notes"
                  value={formData.notes}
                  onChange={handleInputChange}
                />
              </div>
              
              <div className="form-group">
                <p>Servizio: {selectedService.title}</p>
                <p>Prezzo: €{selectedService.price.toFixed(2)}</p>
              </div>
              
              <div className="form-actions">
                <button type="submit" className="confirm-button">Conferma Prenotazione</button>
                <button type="button" className="cancel-button" onClick={() => setSelectedService(null)}>Annulla</button>
              </div>
            </form>
          </div>
        </div>
      )}
      
      {filteredServices.map(service => (
        <ServiceCard 
          key={service.id}
          service={service}
          onBook={handleBookService}
        />
      ))}
    </main>
  );
};

export default ServicesPage;