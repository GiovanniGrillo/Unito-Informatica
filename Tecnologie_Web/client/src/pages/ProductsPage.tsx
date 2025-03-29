// client/src/pages/ProductsPage.tsx
import React, {useState, useEffect} from 'react';
import ProductGrid from '../components/features/ProductGrid';
import ProductFilter from '../components/features/ProductFilter';
import {useCart} from '../contexts/CartContext';
import {useAuth} from '../contexts/AuthContext';
import '../styles/product-grid.css';
import '../styles/filter.css';

import { Product } from '../types/Product';

const ProductsPage: React.FC = () => {
    const [products, setProducts] = useState<Product[]>([]);
    const [filteredProducts, setFilteredProducts] = useState<Product[]>([]);
    const [categories, setCategories] = useState<string[]>([]);
    const [selectedCategory, setSelectedCategory] = useState<string | null>(null);
    const [loading, setLoading] = useState<boolean>(true);
    const [error, setError] = useState<string | null>(null);
    const {addToCart} = useCart();
    const {isAuthenticated} = useAuth();

    useEffect(() => {
        const fetchProducts = async () => {
            try {
                const response = await fetch('http://localhost:8080/products');
                if (!response.ok) {
                    throw new Error('Errore nel caricamento dei prodotti');
                }
                const data = await response.json();
                setProducts(data);
                setFilteredProducts(data);

                // Estrai le categorie uniche dai prodotti
                const uniqueCategories = [...new Set(data.map((product: Product) => product.category))].sort();
                setCategories(uniqueCategories as string[]);
                
                setError(null);
            } catch (error) {
                setError('Si è verificato un errore durante il caricamento dei prodotti.');
                // Imposta prodotti vuoti in caso di errore
                setProducts([]);
                setFilteredProducts([]);
                console.error('Errore:', error);
            } finally {
                setLoading(false);
            }
        };

        fetchProducts().then();
    }, []);

    // Filtra i prodotti quando cambia la categoria selezionata
    useEffect(() => {
        if (selectedCategory) {
            const filtered = products.filter(product => product.category === selectedCategory);
            setFilteredProducts(filtered);
        } else {
            setFilteredProducts(products);
        }
    }, [selectedCategory, products]);

    const handleCategoryChange = (category: string | null) => {
        setSelectedCategory(category);
    };

    const handleAddToCart = (product: Product) => {
        if (isAuthenticated) {
            addToCart(product);
        }
    };

    // Mostriamo sempre il titolo e la descrizione, anche durante il caricamento o in caso di errore
    // come avviene nella pagina servizi

    return (
        <main>
            <section className="content-area">
                <div className="products-container">
                    {/* Intestazione sempre visibile, anche in caso di errore o caricamento */}
                    <div className="products-header">
                        <h2>I Nostri Prodotti</h2>
                        <div className="header-underline"></div>
                        <p>
                            Scopri la nostra selezione di prodotti professionali per la cura dei capelli.
                            Utilizziamo e vendiamo solo prodotti di alta qualità, scelti dai nostri esperti.
                        </p>
                    </div>

                    {/* Mostra messaggio di caricamento se necessario */}
                    {loading && (
                        <div className="loading-message">
                            <p>Caricamento dei prodotti in corso...</p>
                        </div>
                    )}

                    {/* Mostra messaggio di errore se presente, ma mantiene l'intestazione */}
                    {error && (
                        <div className="error-message">
                            <p style={{ color: 'red' }}>Non è possibile caricare la pagina</p>
                        </div>
                    )}

                    {/* Mostra il filtro solo se ci sono categorie disponibili */}
                    {categories.length > 0 && (
                        <ProductFilter
                            categories={categories}
                            selectedCategory={selectedCategory}
                            onCategoryChange={handleCategoryChange}
                        />
                    )}
                    
                    {/* Mostra i prodotti o un messaggio appropriato */}
                    {!loading && !error && (
                        filteredProducts.length === 0 ? (
                            <div className="no-products">
                                <p>Nessun prodotto trovato nella categoria selezionata.</p>
                                <button 
                                    className="button button-accent" 
                                    onClick={() => setSelectedCategory(null)}
                                >
                                    Mostra tutti i prodotti
                                </button>
                            </div>
                        ) : (
                            /* Griglia dei prodotti */
                            <ProductGrid 
                                products={filteredProducts} 
                                onAddToCart={handleAddToCart} 
                            />
                        )
                    )}
                </div>
            </section>
        </main>
    );
};

export default ProductsPage;
