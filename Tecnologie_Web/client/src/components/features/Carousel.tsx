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
    { src: '/img/car// src/components/features/Carousel.tsx\n' +
            'import React from \'react\';\n' +
            '// You need to choose one of these options:\n' +
            '\n' +
            '// Option 1: Use React Bootstrap Carousel (requires react-bootstrap)\n' +
            '/*\n' +
            'import { Carousel as BootstrapCarousel } from \'react-bootstrap\';\n' +
            '\n' +
            'interface CarouselSlide {\n' +
            '  src: string;\n' +
            '  alt: string;\n' +
            '}\n' +
            '\n' +
            'const Carousel: React.FC = () => {\n' +
            '  const slides: CarouselSlide[] = [\n' +
            '    { src: \'/img/carosello_1.webp\', alt: \'Carosello 1\' },\n' +
            '    { src: \'/img/carosello_2.webp\', alt: \'Carosello 2\' },\n' +
            '    { src: \'/img/carosello_3.webp\', alt: \'Carosello 3\' }\n' +
            '  ];\n' +
            '\n' +
            '  return (\n' +
            '    <section className="central-area">\n' +
            '      <BootstrapCarousel \n' +
            '        className="custom-carousel" \n' +
            '        indicators={true}\n' +
            '        controls={true}\n' +
            '        interval={3000}\n' +
            '        pause="hover"\n' +
            '      >\n' +
            '        {slides.map((slide, index) => (\n' +
            '          <BootstrapCarousel.Item key={index}>\n' +
            '            <img\n' +
            '              className="d-block w-100"\n' +
            '              src={slide.src}\n' +
            '              alt={slide.alt}\n' +
            '            />\n' +
            '            <BootstrapCarousel.Caption className="d-none d-md-block">\n' +
            '              <h3>Bellezza Naturale</h3>\n' +
            '              <p>Il tuo salone di bellezza di fiducia</p>\n' +
            '            </BootstrapCarousel.Caption>\n' +
            '          </BootstrapCarousel.Item>\n' +
            '        ))}\n' +
            '      </BootstrapCarousel>\n' +
            '    </section>\n' +
            '  );\n' +
            '};\n' +
            '*/\n' +
            '\n' +
            '// Option 2: Use vanilla JS carousel (no dependencies required)\n' +
            '// This matches your custom carousel CSS\n' +
            'const Carousel: React.FC = () => {\n' +
            '  const slides = [\n' +
            '    { src: \'/img/carosello_1.webp\', alt: \'Carosello 1\' },\n' +
            '    { src: \'/img/carosello_2.webp\', alt: \'Carosello 2\' },\n' +
            '    { src: \'/img/carosello_3.webp\', alt: \'Carosello 3\' }\n' +
            '  ];\n' +
            '\n' +
            '  const [currentSlide, setCurrentSlide] = React.useState(0);\n' +
            '\n' +
            '  const goToSlide = (index: number) => {\n' +
            '    setCurrentSlide(index);\n' +
            '  };\n' +
            '\n' +
            '  const goToNextSlide = () => {\n' +
            '    setCurrentSlide((prev) => (prev === slides.length - 1 ? 0 : prev + 1));\n' +
            '  };\n' +
            '\n' +
            '  const goToPrevSlide = () => {\n' +
            '    setCurrentSlide((prev) => (prev === 0 ? slides.length - 1 : prev - 1));\n' +
            '  };\n' +
            '\n' +
            '  React.useEffect(() => {\n' +
            '    const timer = setInterval(() => {\n' +
            '      goToNextSlide();\n' +
            '    }, 5000);\n' +
            '\n' +
            '    return () => {\n' +
            '      clearInterval(timer);\n' +
            '    };\n' +
            '  }, []);\n' +
            '\n' +
            '  return (\n' +
            '    <section className="central-area">\n' +
            '      <div className="carousel">\n' +
            '        <div \n' +
            '          className="carousel-container" \n' +
            '          style={{ transform: `translateX(-${currentSlide * 100}%)` }}\n' +
            '        >\n' +
            '          {slides.map((slide, index) => (\n' +
            '            <div className="carousel-slide" key={index}>\n' +
            '              <img src={slide.src} alt={slide.alt} />\n' +
            '            </div>\n' +
            '          ))}\n' +
            '        </div>\n' +
            '        \n' +
            '        <button \n' +
            '          className="carousel-control prev" \n' +
            '          onClick={goToPrevSlide}\n' +
            '          aria-label="Previous slide"\n' +
            '        >\n' +
            '          &lt;\n' +
            '        </button>\n' +
            '        \n' +
            '        <button \n' +
            '          className="carousel-control next" \n' +
            '          onClick={goToNextSlide}\n' +
            '          aria-label="Next slide"\n' +
            '        >\n' +
            '          &gt;\n' +
            '        </button>\n' +
            '        \n' +
            '        <div className="carousel-dots">\n' +
            '          {slides.map((_, index) => (\n' +
            '            <button\n' +
            '              key={index}\n' +
            '              className={`carousel-dot ${index === currentSlide ? \'active\' : \'\'}`}\n' +
            '              onClick={() => goToSlide(index)}\n' +
            '              aria-label={`Go to slide ${index + 1}`}\n' +
            '            />\n' +
            '          ))}\n' +
            '        </div>\n' +
            '      </div>\n' +
            '    </section>\n' +
            '  );\n' +
            '};\n' +
            '\n' +
            'export default Carousel;osello_3.webp', alt: 'Carosello 3' }
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
            <BootstrapCarousel.Caption className="d-none d-md-block">
              <h3>Bellezza Naturale</h3>
              <p>Il tuo salone di bellezza di fiducia</p>
            </BootstrapCarousel.Caption>
          </BootstrapCarousel.Item>
        ))}
      </BootstrapCarousel>
    </section>
  );
};

export default Carousel;