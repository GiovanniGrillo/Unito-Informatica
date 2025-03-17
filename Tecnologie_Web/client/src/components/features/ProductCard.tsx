// src/components/features/ProductCard.tsx
import React from 'react';
import { Product } from '../../types/Product';

interface ProductCardProps {
  product: Product;
  onBuy: (productId: number) => void;
}

const ProductCard: React.FC<ProductCardProps> = ({ product, onBuy }) => {
  return (
    <section className="service-box product-box">
      <div className="service-image">
        <img src={product.imageSrc} alt={product.title} loading="lazy" />
      </div>
      <div className="service-text">
        <p className="service-category">{product.category}</p>
        <h2 className="service-title">{product.title} €{product.price}</h2>
        <p className="service-description">{product.description}</p>
        <button 
          className="service-button"
          onClick={() => onBuy(product.id)}
        >
          Acquista Ora
        </button>
      </div>
    </section>
  );
};

export default ProductCard;