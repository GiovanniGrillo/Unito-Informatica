// src/components/features/Gallery.tsx
import React from 'react';

interface GalleryImage {
  src: string;
  alt: string;
}

const Gallery: React.FC = () => {
  const galleryImages: GalleryImage[] = [
    { src: '/img/gallery/gallery_1.png', alt: 'Gallery Image 1' },
    { src: '/img/gallery/gallery_2.png', alt: 'Gallery Image 2' },
    { src: '/img/gallery/gallery_3.png', alt: 'Gallery Image 3' },
    { src: '/img/gallery/gallery_4.png', alt: 'Gallery Image 4' },
    { src: '/img/gallery/gallery_5.png', alt: 'Gallery Image 5' },
    { src: '/img/gallery/gallery_6.png', alt: 'Gallery Image 6' },
    { src: '/img/gallery/gallery_7.png', alt: 'Gallery Image 7' },
    { src: '/img/gallery/gallery_8.png', alt: 'Gallery Image 8' }
  ];

  return (
    <div className="container">
      <section className="gallery">
        {galleryImages.map((image, index) => (
          <div className="gallery-item" key={index}>
            <img src={image.src} alt={image.alt} loading="lazy" />
          </div>
        ))}
      </section>
    </div>
  );
};

export default Gallery;