// Custom script to initialize the carousel
document.addEventListener('DOMContentLoaded', function() {
  // Wait for a short delay to ensure React has rendered the carousel
  setTimeout(function() {
    if (window.$ && typeof window.$ === 'function') {
      try {
        // Check if carousel element exists
        if ($('.carousel').length > 0) {
          // Initialize slick carousel
          $('.carousel').slick({
            dots: true,
            infinite: true,
            speed: 500,
            fade: true,
            cssEase: 'linear',
            autoplay: true,
            autoplaySpeed: 3000,
            arrows: true
          });
          console.log('Carousel initialized successfully from external script');
        } else {
          console.error('Carousel element not found in the DOM');
        }
      } catch (e) {
        console.error('Error initializing carousel from external script:', e);
      }
    } else {
      console.error('jQuery is not available for carousel initialization');
    }
  }, 500); // 500ms delay to ensure DOM is fully rendered
});