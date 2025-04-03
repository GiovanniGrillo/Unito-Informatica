// src/components/features/AddProductForm.tsx
import React, { useState, useEffect } from 'react';
import { Product } from '../../types/Product';

interface AddProductFormProps {
  categories: string[];
  onSubmit: (product: Omit<Product, 'id'>) => void;
  onCancel: () => void;
  initialData?: Omit<Product, 'id'>;
}

const AddProductForm: React.FC<AddProductFormProps> = ({ categories, onSubmit, onCancel, initialData }) => {
  const [formData, setFormData] = useState<Omit<Product, 'id'>>({ 
    name: initialData?.name || '',
    category: initialData?.category || (categories.length > 0 ? categories[0] : ''),
    price: initialData?.price || 0,
    description: initialData?.description || '',
    imageUrl: initialData?.imageUrl || '',
    availableQuantity: initialData?.availableQuantity || 0
  });
  
  // Aggiorna il form quando cambiano i dati iniziali
  useEffect(() => {
    if (initialData) {
      setFormData({
        name: initialData.name,
        category: initialData.category,
        price: initialData.price,
        description: initialData.description,
        imageUrl: initialData.imageUrl,
        availableQuantity: initialData.availableQuantity || 0
      });
    }
  }, [initialData]);

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

      <div className="form-actions" style={{ justifyContent: 'flex-start' }}>
        <button type="button" className="button button-secondary cancel-button" onClick={onCancel}>
          Annulla
        </button>
        <button type="submit" className="button button-primary confirm-button">
          Conferma
        </button>
      </div>
    </form>
  );
};

export default AddProductForm;