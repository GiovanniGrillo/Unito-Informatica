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

interface CartItem {
  productId: number;
  quantity: number;
  name: string;
  price: number;
}

const ProductsPage: React.FC = () => {
  const [products, setProducts] = useState<Product[]>([]);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);
  const [cart, setCart] = useState<CartItem[]>([]);
  const [selectedProduct, setSelectedProduct] = useState<Product | null>(null);
  const [quantity, setQuantity] = useState<number>(1);
  const [orderSuccess, setOrderSuccess] = useState<boolean>(false);
  const [orderError, setOrderError] = useState<string | null>(null);

  useEffect(() => {
    const fetchProducts = async () => {
      try {
        const response = await fetch('http://localhost:8080/api/products');
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

  const handleAddToCart = (product: Product) => {
    setSelectedProduct(product);
    setQuantity(1);
  };

  const handleQuantityChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const value = parseInt(e.target.value);
    if (value > 0 && selectedProduct && value <= selectedProduct.availableQuantity) {
      setQuantity(value);
    }
  };

  const handleSubmitOrder = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!selectedProduct) return;

    try {
      // Preparazione dei dati per l'invio al server
      const orderData = {
        productId: selectedProduct.id,
        quantity: quantity,
        userId: 1, // In un'app reale, questo verrebbe dall'autenticazione
      };

      // Invio della richiesta POST al server
      const response = await fetch('http://localhost:8080/api/orders', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(orderData),
      });

      if (!response.ok) {
        throw new Error('Errore nell\'invio dell\'ordine');
      }

      // Aggiornamento del carrello
      const newCartItem: CartItem = {
        productId: selectedProduct.id,
        quantity: quantity,
        name: selectedProduct.name,
        price: selectedProduct.price
      };

      setCart([...cart, newCartItem]);
      setSelectedProduct(null);
      setOrderSuccess(true);
      setOrderError(null);

      // Aggiornamento della quantità disponibile del prodotto
      const updatedProducts = products.map(p => {
        if (p.id === selectedProduct.id) {
          return { ...p, availableQuantity: p.availableQuantity - quantity };
        }
        return p;
      });
      setProducts(updatedProducts);

    } catch (error) {
      setOrderError('Si è verificato un errore durante l\'invio dell\'ordine.');
      console.error('Errore:', error);
    }
  };

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

        {orderSuccess && (
          <div className="success-message">
            Prodotto aggiunto al carrello con successo!
            <button onClick={() => setOrderSuccess(false)}>Chiudi</button>
          </div>
        )}

        {orderError && (
          <div className="error-message">
            {orderError}
            <button onClick={() => setOrderError(null)}>Chiudi</button>
          </div>
        )}

        {selectedProduct && (
          <div className="product-form-overlay">
            <div className="product-form-container">
              <h3>Acquista {selectedProduct.name}</h3>
              <form onSubmit={handleSubmitOrder}>
                <div className="form-group">
                  <label htmlFor="quantity">Quantità:</label>
                  <input
                    type="number"
                    id="quantity"
                    min="1"
                    max={selectedProduct.availableQuantity}
                    value={quantity}
                    onChange={handleQuantityChange}
                  />
                  <p>Disponibilità: {selectedProduct.availableQuantity}</p>
                </div>
                <div className="form-group">
                  <p>Prezzo totale: €{(selectedProduct.price * quantity).toFixed(2)}</p>
                </div>
                <div className="form-actions">
                  <button type="submit" className="confirm-button">Conferma Acquisto</button>
                  <button type="button" className="cancel-button" onClick={() => setSelectedProduct(null)}>Annulla</button>
                </div>
              </form>
            </div>
          </div>
        )}

        {cart.length > 0 && (
          <div className="cart-summary">
            <h3>Carrello ({cart.length})</h3>
            <ul>
              {cart.map((item, index) => (
                <li key={index}>
                  {item.name} - Quantità: {item.quantity} - €{(item.price * item.quantity).toFixed(2)}
                </li>
              ))}
            </ul>
            <p>Totale: €{cart.reduce((total, item) => total + (item.price * item.quantity), 0).toFixed(2)}</p>
          </div>
        )}

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
                  <button 
                    className="buy-button" 
                    onClick={() => handleAddToCart(product)}
                    disabled={product.availableQuantity <= 0}
                  >
                    {product.availableQuantity <= 0 ? 'Esaurito' : 'Aggiungi al carrello'}
                  </button>
                </div>
              </div>
          ))}
        </div>
      </main>
  );
};

export default ProductsPage;
