import React, { useState, useEffect } from 'react';

const Carousel: React.FC = () => {
  const [currentSlide, setCurrentSlide] = useState(0);
  const slides = [
    { src: '/img/carosello_1.webp', alt: 'Carosello 1' },
    { src: '/img/carosello_2.webp', alt: 'Carosello 2' },
    { src: '/img/carosello_3.webp', alt: 'Carosello 3' }
  ];

  // Auto-advance slides
  useEffect(() => {
    const interval = setInterval(() => {
      setCurrentSlide((prev) => (prev + 1) % slides.length);
    }, 3000);
    
    return () => clearInterval(interval);
  }, [slides.length]);

  // Handle manual navigation
  const goToSlide = (index: number): void => {
    setCurrentSlide(index);
  };

  const goToPrevSlide = (): void => {
    setCurrentSlide((prev) => (prev - 1 + slides.length) % slides.length);
  };

  const goToNextSlide = (): void => {
    setCurrentSlide((prev) => (prev + 1) % slides.length);
  };

  return (
    <section className="central-area">
      <div className="carousel">
        <div className="carousel-container">
          {slides.map((slide, index) => (
            <div 
              key={index}
              className={`carousel-slide ${index === currentSlide ? 'active' : ''}`}
              style={{ transform: `translateX(${100 * (index - currentSlide)}%)` }}
            >
              <img src={slide.src} alt={slide.alt} />
            </div>
          ))}
        </div>
        
        <button className="carousel-control prev" onClick={goToPrevSlide}>
          &lt;
        </button>
        <button className="carousel-control next" onClick={goToNextSlide}>
          &gt;
        </button>
        
        <div className="carousel-dots">
          {slides.map((_, index) => (
            <button 
              key={index} 
              className={`carousel-dot ${index === currentSlide ? 'active' : ''}`}
              onClick={() => goToSlide(index)}
            />
          ))}
        </div>
      </div>
    </section>
  );
};

export default Carousel;