import React, { useState, useEffect } from 'react';
import ServiceCard, { Service } from '../components/features/ServiceCard';
import ServiceFilter from '../components/features/ServiceFilter';
import '../styles/services.css';

const ServicesPage: React.FC = () => {

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
  
  // Reindirizzamento alla pagina di prenotazione
  const handleBookService = (serviceId: number) => {
    // Qui puoi implementare la navigazione alla pagina di prenotazione
    console.log(`Navigazione alla pagina di prenotazione per il servizio ${serviceId}`);
    // Esempio: window.location.href = '/prenota-ora';
  };

  return (
    <main>
      <section className="services-header">
        <h2>Servizi</h2>
        <p>
          Offriamo una gamma di servizi per la cura e lo styling dei capelli, con prodotti di alta qualità e tecniche avanzate.
        </p>
      </section>
      
      <section className="services-content-area">
          {/* Componente di filtro */}
          {categories.length > 0 && (
            <ServiceFilter 
              categories={categories}
              selectedCategory={selectedCategory}
              onCategoryChange={handleCategoryChange}
            />
          )}
      </section>
      
      {loading && (
        <div className="loading-message">
          <p>Caricamento dei servizi in corso...</p>
        </div>
      )}
      
      {error && (
        <div className="error-message">
          <p style={{ color: 'red' }}>Non è possibile caricare la pagina</p>
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