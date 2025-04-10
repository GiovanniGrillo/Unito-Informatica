import React, { useEffect } from 'react';
import { useCart } from '../../contexts/CartContext';
import { useAuth } from '../../contexts/AuthContext';
import '../../styles/cart.css';

const Cart: React.FC = () => {
  const { 
    cartItems, 
    removeFromCart, 
    updateQuantity, 
    clearCart, 
    getTotalPrice, 
    isCartOpen, 
    toggleCart 
  } = useCart();
  const { isAuthenticated } = useAuth();

  // Aggiungi event listener per il tasto ESC
  useEffect(() => {
    const handleEscKey = (event: KeyboardEvent) => {
      if (event.key === 'Escape' && isCartOpen) {
        toggleCart();
      }
    };

    // Aggiungi l'event listener quando il componente viene montato
    window.addEventListener('keydown', handleEscKey);

    // Rimuovi l'event listener quando il componente viene smontato
    return () => {
      window.removeEventListener('keydown', handleEscKey);
    };
  }, [isCartOpen, toggleCart]);

  // Verifica sia lo stato di autenticazione che lo stato di apertura del carrello
  if (!isCartOpen || !isAuthenticated) {
    return null;
  }

  return (
    <div className="cart-overlay">
      <div className="cart-container">
        <div className="cart-header">
          <h2>Il tuo carrello</h2>
          <button className="close-cart" onClick={toggleCart}>×</button>
        </div>
        
        {cartItems.length === 0 ? (
          <div className="empty-cart">
            <p>Il tuo carrello è vuoto</p>
          </div>
        ) : (
          <>
            <div className="cart-items">
              {cartItems.map(item => {
                // Verifica che l'item abbia tutte le proprietà necessarie
                if (!item || !item.id) {
                  return null; // Salta gli elementi non validi
                }
                
                return (
                  <div className="cart-item" key={item.id}>
                    <div className="cart-item-image">
                      {/* Gestione errori per immagini non valide */}
                      <img 
                        src={item.imageUrl || '/img/placeholder.png'} 
                        alt={item.name || 'Prodotto'} 
                        loading="lazy" 
                        onError={(e) => {
                          // Fallback per immagini non caricate
                          e.currentTarget.src = '/img/placeholder.png';
                        }}
                      />
                    </div>
                    <div className="cart-item-details">
                      <h3>{item.name || 'Prodotto sconosciuto'}</h3>
                      <p className="cart-item-price">€{(item.price || 0).toFixed(2)}</p>
                    </div>
                    <div className="cart-item-quantity">
                      <button 
                        onClick={() => updateQuantity(item.id, item.quantity - 1)}
                        className="quantity-btn"
                      >
                        -
                      </button>
                      <span>{item.quantity || 1}</span>
                      <button 
                        onClick={() => updateQuantity(item.id, item.quantity + 1)}
                        className="quantity-btn"
                        disabled={item.availableQuantity !== undefined && item.quantity >= item.availableQuantity}
                      >
                        +
                      </button>
                    </div>
                    <button 
                      className="remove-item" 
                      onClick={() => removeFromCart(item.id)}
                    >
                      Rimuovi
                    </button>
                  </div>
                );
              })}
            </div>
            
            <div className="cart-footer">
              <div className="cart-total">
                <span>Totale:</span>
                <span>€{getTotalPrice().toFixed(2)}</span>
              </div>
              <div className="cart-actions">
                <button className="clear-cart" onClick={clearCart}>Svuota carrello</button>
                <button className="checkout">Procedi all'acquisto</button>
              </div>
            </div>
          </>
        )}
      </div>
    </div>
  );
};

export default Cart;