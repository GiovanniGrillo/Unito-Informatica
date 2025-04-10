import React from 'react';
import '../../styles/gallery.css';

interface GalleryImage {
  src: string;
  alt: string;
}

const Gallery: React.FC = () => {
  const galleryImages: GalleryImage[] = [
    { src: '/img/gallery/gallery_1.png', alt: 'Sala tagli' },
    { src: '/img/gallery/gallery_2.png', alt: 'Reception' },
    { src: '/img/gallery/gallery_3.png', alt: 'Sala VIP' },
    { src: '/img/gallery/gallery_4.png', alt: 'Area attesa' },
    { src: '/img/gallery/gallery_5.png', alt: 'Sala tagli' },
    { src: '/img/gallery/gallery_6.png', alt: 'Vetrina prodotti' },
    { src: '/img/gallery/gallery_7.png', alt: 'Sala lavaggio' },
    { src: '/img/gallery/gallery_8.png', alt: 'Sala styling' }
  ];

  return (
    <div className="gallery-container">
      <section className="gallery-grid">
        {galleryImages.map((image, index) => (
          <div className="gallery-item" key={index}>
            <img src={image.src} alt={image.alt} loading="lazy" />
            <div className="gallery-item-overlay">
              <p>{image.alt}</p>
            </div>
          </div>
        ))}
      </section>
    </div>
  );
};

export default Gallery;