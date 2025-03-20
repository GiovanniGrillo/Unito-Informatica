// src/types/Product.ts
export interface Product {
  id: number;
  category: string;
  name: string;
  price: number;
  description: string;
  imageUrl: string;
  availableQuantity?: number;
}