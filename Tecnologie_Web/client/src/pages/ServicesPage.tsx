// src/pages/ServicesPage.tsx
import React, { useState } from 'react';
import ServiceCard from '../components/features/ServiceCard';
import { Service } from '../types/Service';

const ServicesPage: React.FC = () => {
  // Stato per tenere traccia del servizio selezionato (esempio di comunicazione tra componenti)
  const [selectedService, setSelectedService] = useState<number | null>(null);
  
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
    setSelectedService(serviceId);
    // In un'app reale, qui potresti aprire un modale di conferma o navigare a un form di prenotazione
    alert(`Servizio selezionato: ${services.find(s => s.id === serviceId)?.title}`);
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
      
      {/* Se c'è un servizio selezionato, mostra un box informativo (esempio di comunicazione tra componenti) */}
      {selectedService && (
        <div className="selected-service-info">
          <p>Hai selezionato: {services.find(s => s.id === selectedService)?.title}</p>
          <button onClick={() => setSelectedService(null)}>Annulla selezione</button>
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