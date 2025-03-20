    // src/components/features/ServiceCard.tsx
import React from 'react';
import { Service } from '../../types/Service';

interface ServiceCardProps {
  service: Service;
  onBook: (serviceId: number) => void;
}

const ServiceCard: React.FC<ServiceCardProps> = ({ service, onBook }) => {
  return (
    <section className="service-box">
      <div className="service-image">
        <img src={service.imageSrc} alt={service.title} loading="lazy" />
      </div>
      <div className="service-text">
        <p className="service-category">{service.category}</p>
        <h2 className="service-title">{service.title} €{service.price}</h2>
        <p className="service-description">{service.description}</p>
        <button 
          className="service-button"
          onClick={() => onBook(service.id)}
        >
          Prenota Online
        </button>
      </div>
    </section>
  );
};

export default ServiceCard;