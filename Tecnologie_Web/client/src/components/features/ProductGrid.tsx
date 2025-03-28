// src/components/features/ProductGrid.tsx
import React from 'react';
import { Product } from '../../types/Product';
import { useAuth } from '../../contexts/AuthContext';
import '../../styles/product-grid.css';

interface ProductGridProps {
  products: Product[];
  onAddToCart: (product: Product) => void;
}

const ProductGrid: React.FC<ProductGridProps> = ({ products, onAddToCart }) => {
  const { isAuthenticated } = useAuth();

  return (
    <div className="products-container">
      <div className="products-grid">
        {products.map((product) => (
          <div className="product-card" key={product.id}>
            <div className="product-image">
              <img src={product.imageUrl} alt={product.name} loading="lazy" />
            </div>
            <div className="product-info">
              <div className="product-category">{product.category}</div>
              <h3 className="product-name">{product.name}</h3>
              <div className="product-price">€{product.price.toFixed(2)}</div>
              <p className="product-description">{product.description}</p>
              
              {product.availableQuantity !== undefined && (
                <div 
                  className={`product-availability ${product.availableQuantity > 0 ? 'in-stock' : 'out-of-stock'}`}
                >
                  {product.availableQuantity > 0 
                    ? `Disponibilità: ${product.availableQuantity} in magazzino` 
                    : "Prodotto esaurito"}
                </div>
              )}
              
              <button 
                className="buy-button"
                onClick={() => onAddToCart(product)}
                disabled={!isAuthenticated || (product.availableQuantity !== undefined && product.availableQuantity <= 0)}
              >
                {!isAuthenticated 
                  ? "Accedi per acquistare" 
                  : product.availableQuantity !== undefined && product.availableQuantity <= 0 
                    ? "Esaurito" 
                    : "Aggiungi al carrello"}
              </button>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default ProductGrid;