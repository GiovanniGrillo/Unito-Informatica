// client/src/pages/ProductsPage.tsx
import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';

interface Product {
  id: number;
  name: string;
  description: string;
  price: number;
  availableQuantity: number;
  category: string;
  imageUrl: string;
}

const ProductsPage: React.FC = () => {
  const [products, setProducts] = useState<Product[]>([]);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const fetchProducts = async () => {
      try {
        const response = await fetch('http://localhost:8080/products');
        if (!response.ok) {
          throw new Error('Errore nel caricamento dei prodotti');
        }
        const data = await response.json();
        setProducts(data);
        setLoading(false);
      } catch (error) {
        setError('Si è verificato un errore durante il caricamento dei prodotti.');
        setLoading(false);
        console.error('Errore:', error);
      }
    };

    fetchProducts();
  }, []);

  if (loading) {
    return <div className="loading">Caricamento prodotti...</div>;
  }

  if (error) {
    return <div className="error">{error}</div>;
  }

  return (
      <main>
        <section className="content-area">
          <div className="section" id="prodotti">
            <h2>I Nostri Prodotti</h2>
            <p>
              Scopri la nostra selezione di prodotti professionali per la cura dei capelli.
              Utilizziamo e vendiamo solo prodotti di alta qualità, scelti dai nostri esperti.
            </p>
          </div>
        </section>

        <div className="products-grid">
          {products.map((product) => (
              <div className="product-card" key={product.id}>
                <div className="product-image">
                  <img src={product.imageUrl} alt={product.name} loading="lazy" />
                </div>
                <div className="product-info">
                  <h3 className="product-name">{product.name}</h3>
                  <p className="product-category">{product.category}</p>
                  <p className="product-price">€{product.price.toFixed(2)}</p>
                  <p className="product-description">{product.description}</p>
                  <p className="product-availability">
                    {product.availableQuantity > 0 
                      ? `Disponibilità: ${product.availableQuantity} in magazzino` 
                      : "Prodotto esaurito"}
                  </p>
                </div>
              </div>
          ))}
        </div>
      </main>
  );
};

export default ProductsPage;
