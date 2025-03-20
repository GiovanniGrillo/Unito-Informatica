// src/components/features/Carousel.tsx
import React from 'react';
import { Carousel as BootstrapCarousel } from 'react-bootstrap';

interface CarouselSlide {
  src: string;
  alt: string;
}

const Carousel: React.FC = () => {
  const slides: CarouselSlide[] = [
    { src: '/img/carosello_1.webp', alt: 'Carosello 1' },
    { src: '/img/carosello_2.webp', alt: 'Carosello 2' },
    { src: '/img/carosello_3.webp', alt: 'Carosello 3' }
  ];

  return (
    <section className="central-area">
      <BootstrapCarousel 
        className="custom-carousel" 
        indicators={true}
        controls={true}
        interval={3000}
        pause="hover"
      >
        {slides.map((slide, index) => (
          <BootstrapCarousel.Item key={index}>
            <img
              className="d-block w-100"
              src={slide.src}
              alt={slide.alt}
            />

          </BootstrapCarousel.Item>
        ))}
      </BootstrapCarousel>
    </section>
  );
};

export default Carousel;