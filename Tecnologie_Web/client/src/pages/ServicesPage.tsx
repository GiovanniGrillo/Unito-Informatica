// src/pages/ServicesPage.tsx
import React, { useState } from 'react';
import ServiceCard from '../components/features/ServiceCard';
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
  
  // Dati di esempio (verrebbero recuperati da un'API in un'app reale)
  const services: Service[] = [
    {
      id: 1,
      category: "TAGLI E PIEGHE PER UOMO A MILANO",
      title: "Taglio Uomo",
      price: 30,
      description: "Affidati a degli esperti del taglio per dare nuova vita alla tua chioma: sapranno ascoltarti e capire il tuo stile per tagliare e rasare esattamente come vuoi tu.",
      imageSrc: "/img/hair_styles/man_cut.webp",
    },
    {
      id: 2,
      category: "TAGLI E PIEGHE PER DONNA A MILANO",
      title: "Taglio Donna",
      price: 40,
      description: "Affidati ai nostri hairstylist per un look personalizzato e alla moda. Dalla piega al taglio su misura, ci prendiamo cura dei tuoi capelli con prodotti di alta qualità.",
      imageSrc: "/img/hair_styles/woman_cut.webp",
    },
    {
      id: 3,
      category: "STYLING E PIEGA A MILANO",
      title: "Piega",
      price: 25,
      description: "Valorizza il tuo look con una piega professionale su misura per te. Che tu voglia capelli lisci, mossi o voluminosi, i nostri esperti sapranno esaltare la tua bellezza naturale.",
      imageSrc: "/img/hair_styles/blow_dry.webp",
    },
    {
      id: 4,
      category: "PERMANENTE PROFESSIONALE A MILANO",
      title: "Permanente",
      price: 60,
      description: "Dona ai tuoi capelli volume e onde perfette con la nostra permanente su misura. I nostri specialisti utilizzeranno tecniche avanzate per garantirti un risultato naturale e duraturo.",
      imageSrc: "/img/hair_styles/hair_perm.webp",
    },
    {
      id: 5,
      category: "COLORAZIONE PROFESSIONALE A MILANO",
      title: "Tinta",
      price: 100,
      description: "Rinnova il tuo look con una colorazione personalizzata. Dai colori naturali ai toni più audaci, i nostri esperti ti aiuteranno a scegliere la nuance perfetta per il tuo stile.",
      imageSrc: "/img/hair_styles/hair_dye.webp",
    }
  ];

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
          <ul>
            <li>Taglio e styling personalizzato</li>
            <li>Colore e trattamenti per capelli</li>
            <li>Trattamenti ristrutturanti</li>
            <li>Acconciature per eventi</li>
          </ul>
        </div>
      </section>
      
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
      
      {services.map(service => (
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