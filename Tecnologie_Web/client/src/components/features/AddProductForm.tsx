// src/components/features/AddProductForm.tsx
import React, { useState } from 'react';
import { Product } from '../../types/Product';

interface AddProductFormProps {
  categories: string[];
  onSubmit: (product: Omit<Product, 'id'>) => void;
  onCancel: () => void;
}

const AddProductForm: React.FC<AddProductFormProps> = ({ categories, onSubmit, onCancel }) => {
  const [formData, setFormData] = useState<Omit<Product, 'id'>>({ 
    name: '',
    category: categories.length > 0 ? categories[0] : '',
    price: 0,
    description: '',
    imageUrl: '',
    availableQuantity: 0
  });

  const handleChange = (e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement | HTMLSelectElement>) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: name === 'price' || name === 'availableQuantity' ? parseFloat(value) : value
    }));
  };

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    onSubmit(formData);
  };

  return (
    <form onSubmit={handleSubmit} className="add-product-form">
      <div className="form-group">
        <label htmlFor="name">Nome Prodotto</label>
        <input
          type="text"
          id="name"
          name="name"
          value={formData.name}
          onChange={handleChange}
          required
        />
      </div>

      <div className="form-group">
        <label htmlFor="category">Categoria</label>
        <select
          id="category"
          name="category"
          value={formData.category}
          onChange={handleChange}
          required
        >
          {categories.map(category => (
            <option key={category} value={category}>
              {category}
            </option>
          ))}
        </select>
      </div>

      <div className="form-group">
        <label htmlFor="price">Prezzo (€)</label>
        <input
          type="number"
          id="price"
          name="price"
          min="0"
          step="0.01"
          value={formData.price}
          onChange={handleChange}
          required
        />
      </div>

      <div className="form-group">
        <label htmlFor="description">Descrizione</label>
        <textarea
          id="description"
          name="description"
          value={formData.description}
          onChange={handleChange}
          required
        />
      </div>

      <div className="form-group">
        <label htmlFor="imageUrl">URL Immagine</label>
        <input
          type="url"
          id="imageUrl"
          name="imageUrl"
          value={formData.imageUrl}
          onChange={handleChange}
          required
        />
      </div>

      <div className="form-group">
        <label htmlFor="availableQuantity">Quantità Disponibile</label>
        <input
          type="number"
          id="availableQuantity"
          name="availableQuantity"
          min="0"
          value={formData.availableQuantity}
          onChange={handleChange}
          required
        />
      </div>

      <div className="form-actions">
        <button type="button" className="button button-secondary" onClick={onCancel}>
          Annulla
        </button>
        <button type="submit" className="button button-primary">
          Conferma
        </button>
      </div>
    </form>
  );
};

export default AddProductForm;