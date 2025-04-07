// src/components/features/ProductGrid.tsx
import React from 'react';
// import { Product } from '../../types/Product'; // Rimosso perché ora definiamo il tipo qui
import { useAuth } from '../../contexts/AuthContext';
import '../../styles/product-grid.css';
import { FaEdit, FaTrash } from 'react-icons/fa';

// Definizione del tipo Product spostata qui dalla cartella types
export interface Product {
  id: number;
  category: string;
  name: string;
  price: number;
  description: string;
  imageUrl: string;
  availableQuantity?: number;
}

interface ProductGridProps {
  products: Product[];
  onAddToCart: (product: Product) => void;
  onEditProduct?: (product: Product) => void;
  onDeleteProduct?: (product: Product) => void;
}

const ProductGrid: React.FC<ProductGridProps> = ({ products, onAddToCart, onEditProduct, onDeleteProduct }) => {
  const { isAuthenticated, isAdmin } = useAuth();

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
              
              {isAuthenticated && isAdmin() && (
                <div className="admin-actions">
                  <button 
                    className="button button-primary"
                    onClick={() => onEditProduct && onEditProduct(product)}
                    title="Modifica prodotto"
                  >
                    <FaEdit /> Modifica
                  </button>
                  <button 
                    className="button button-accent"
                    onClick={() => onDeleteProduct && onDeleteProduct(product)}
                    title="Elimina prodotto"
                  >
                    <FaTrash /> Elimina
                  </button>
                </div>
              )}
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default ProductGrid;