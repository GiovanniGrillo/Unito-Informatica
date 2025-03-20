// src/components/features/ProductCard.tsx
import React from 'react';
import { Product } from '../../types/Product';
import '../styles/products-box.css';

interface ProductCardProps {
  product: Product;
  onBuy: (productId: number) => void;
}

const ProductCard: React.FC<ProductCardProps> = ({ product, onBuy }) => {
  return (
    <section className="service-box product-box">
      <div className="service-image">
        <img src={product.imageUrl} alt={product.name} loading="lazy" />
      </div>
      <div className="product-text">
        <p className="service-category">{product.category}</p>
        <h2 className="service-title">{product.name} <span className="product-price">€{product.price.toFixed(2)}</span></h2>
        <p className="service-description">{product.description}</p>
        {product.availableQuantity !== undefined && (
          <p className="product-availability">
            {product.availableQuantity > 0 
              ? `Disponibilità: ${product.availableQuantity} in magazzino` 
              : "Prodotto esaurito"}
          </p>
        )}
        <button 
          className="service-button"
          onClick={() => onBuy(product.id)}
          disabled={product.availableQuantity !== undefined && product.availableQuantity <= 0}
        >
          {product.availableQuantity !== undefined && product.availableQuantity <= 0 
            ? "Esaurito" 
            : "Acquista Ora"}
        </button>
      </div>
    </section>
  );
};

export default ProductCard;