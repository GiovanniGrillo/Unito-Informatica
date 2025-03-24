// src/components/features/ServiceFilter.tsx
import React from 'react';
import '../../styles/filter.css';

interface ServiceFilterProps {
  categories: string[];
  selectedCategory: string | null;
  onCategoryChange: (category: string | null) => void;
}

const ServiceFilter: React.FC<ServiceFilterProps> = ({ 
  categories, 
  selectedCategory, 
  onCategoryChange 
}) => {
  return (
    <div className="filter-container">
      <h3 className="filter-title">Filtra per Categoria</h3>
      <div className="filter-options">
        {categories.map((category) => (
          <button
            key={category}
            className={`filter-option ${selectedCategory === category ? 'active' : ''}`}
            onClick={() => onCategoryChange(selectedCategory === category ? null : category)}
          >
            {category}
          </button>
        ))}
      </div>
      {selectedCategory && (
        <button 
          className="filter-clear" 
          onClick={() => onCategoryChange(null)}
        >
          Rimuovi filtro
        </button>
      )}
    </div>
  );
};

export default ServiceFilter;