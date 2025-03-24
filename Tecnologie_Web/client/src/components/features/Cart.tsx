// src/components/features/Cart.tsx
import React from 'react';
import { useCart } from '../../contexts/CartContext';
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

  if (!isCartOpen) {
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
              {cartItems.map(item => (
                <div className="cart-item" key={item.id}>
                  <div className="cart-item-image">
                    <img src={item.imageUrl} alt={item.name} loading="lazy" />
                  </div>
                  <div className="cart-item-details">
                    <h3>{item.name}</h3>
                    <p className="cart-item-price">€{item.price.toFixed(2)}</p>
                  </div>
                  <div className="cart-item-quantity">
                    <button 
                      onClick={() => updateQuantity(item.id, item.quantity - 1)}
                      className="quantity-btn"
                    >
                      -
                    </button>
                    <span>{item.quantity}</span>
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
              ))}
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