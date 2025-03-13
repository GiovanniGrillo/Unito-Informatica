import React from 'react';

interface ServiceBoxProps {
  category: string;
  title: string;
  description: string;
  imageSrc: string;
  imageAlt: string;
}

const ServiceBox: React.FC<ServiceBoxProps> = ({ 
  category, 
  title, 
  description, 
  imageSrc, 
  imageAlt 
}) => {
  return (
    <section className="service-box">
      <div className="service-image">
        <img src={imageSrc} alt={imageAlt} loading="lazy" />
      </div>
      <div className="service-text">
        <p className="service-category">{category}</p>
        <h2 className="service-title">{title}</h2>
        <p className="service-description">{description}</p>
        <button className="service-button">Prenota Online</button>
      </div>
    </section>
  );
};

export default ServiceBox;