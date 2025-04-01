// client/src/pages/ProductsPage.tsx
import React, {useState, useEffect} from 'react';
import ProductGrid from '../components/features/ProductGrid';
import ProductFilter from '../components/features/ProductFilter';
import Popup from '../components/features/Popup';
import {useCart} from '../contexts/CartContext';
import {useAuth} from '../contexts/AuthContext';
import '../styles/product-grid.css';
import '../styles/filter.css';
import '../styles/popup.css';
import '../styles/products-actions.css';

import { Product } from '../types/Product';

const ProductsPage: React.FC = () => {
    const [products, setProducts] = useState<Product[]>([]);
    const [filteredProducts, setFilteredProducts] = useState<Product[]>([]);
    const [categories, setCategories] = useState<string[]>([]);
    const [selectedCategory, setSelectedCategory] = useState<string | null>(null);
    const [loading, setLoading] = useState<boolean>(true);
    const [error, setError] = useState<string | null>(null);
    const [showAddModal, setShowAddModal] = useState<boolean>(false);
    const [showInfoModal, setShowInfoModal] = useState<boolean>(false);
    const [newProduct, setNewProduct] = useState<Partial<Product>>({});
    const {addToCart} = useCart();
    const {isAuthenticated, isAdmin} = useAuth();

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

    // Gestione del form per l'aggiunta di un nuovo prodotto
    const handleInputChange = (e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>) => {
        const { name, value } = e.target;
        setNewProduct(prev => ({
            ...prev,
            [name]: name === 'price' || name === 'availableQuantity' ? parseFloat(value) : value
        }));
    };

    // Funzione per aggiungere un nuovo prodotto
    const handleAddProduct = async (e: React.FormEvent) => {
        e.preventDefault();
        try {
            const response = await fetch('http://localhost:8080/products', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(newProduct),
            });

            if (response.ok) {
                // Aggiorna la lista dei prodotti dopo l'aggiunta
                const updatedProducts = await response.json();
                setProducts(prevProducts => [...prevProducts, updatedProducts]);
                setFilteredProducts(prevProducts => [...prevProducts, updatedProducts]);
                setShowAddModal(false);
                setNewProduct({});
            } else {
                console.error('Errore durante l\'aggiunta del prodotto');
            }
        } catch (error) {
            console.error('Errore:', error);
        }
    };

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
                    
                    {/* Pulsanti di azione per gli amministratori */}
                    {isAuthenticated && isAdmin() && (
                        <div className="products-actions">
                            <button 
                                className="button button-primary" 
                                onClick={() => setShowAddModal(true)}
                            >
                                Aggiungi Prodotto
                            </button>
                            <button 
                                className="button button-accent" 
                                onClick={() => setShowInfoModal(true)}
                            >
                                Informazioni
                            </button>
                        </div>
                    )}

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
            
            {/* Modale per aggiungere un nuovo prodotto */}
            <Popup 
                isOpen={showAddModal} 
                onClose={() => setShowAddModal(false)} 
                title="Aggiungi Nuovo Prodotto"
                footer={
                    <div className="form-actions">
                        <button type="submit" className="button button-primary" form="addProductForm">Salva</button>
                        <button type="button" className="button button-accent" onClick={() => setShowAddModal(false)}>Annulla</button>
                    </div>
                }
            >
                <form id="addProductForm" onSubmit={handleAddProduct}>
                    <div className="form-group">
                        <label htmlFor="name">Nome Prodotto</label>
                        <input 
                            type="text" 
                            id="name" 
                            name="name" 
                            value={newProduct.name || ''} 
                            onChange={handleInputChange} 
                            required 
                        />
                    </div>
                    <div className="form-group">
                        <label htmlFor="category">Categoria</label>
                        <input 
                            type="text" 
                            id="category" 
                            name="category" 
                            value={newProduct.category || ''} 
                            onChange={handleInputChange} 
                            required 
                        />
                    </div>
                    <div className="form-group">
                        <label htmlFor="price">Prezzo (€)</label>
                        <input 
                            type="number" 
                            id="price" 
                            name="price" 
                            step="0.01" 
                            value={newProduct.price || ''} 
                            onChange={handleInputChange} 
                            required 
                        />
                    </div>
                    <div className="form-group">
                        <label htmlFor="description">Descrizione</label>
                        <textarea 
                            id="description" 
                            name="description" 
                            value={newProduct.description || ''} 
                            onChange={handleInputChange} 
                            required 
                        />
                    </div>
                    <div className="form-group">
                        <label htmlFor="imageUrl">URL Immagine</label>
                        <input 
                            type="text" 
                            id="imageUrl" 
                            name="imageUrl" 
                            value={newProduct.imageUrl || ''} 
                            onChange={handleInputChange} 
                            required 
                        />
                    </div>
                    <div className="form-group">
                        <label htmlFor="availableQuantity">Quantità Disponibile</label>
                        <input 
                            type="number" 
                            id="availableQuantity" 
                            name="availableQuantity" 
                            value={newProduct.availableQuantity || ''} 
                            onChange={handleInputChange} 
                            required 
                        />
                    </div>
                </form>
            </Popup>
            
            {/* Modale per le informazioni */}
            <Popup 
                isOpen={showInfoModal} 
                onClose={() => setShowInfoModal(false)} 
                title="Informazioni sui Prodotti"
                footer={
                    <div className="form-actions">
                        <button className="button button-accent" onClick={() => setShowInfoModal(false)}>Chiudi</button>
                    </div>
                }
            >
                <div className="info-content">
                    <p>Questa sezione permette di gestire i prodotti del negozio.</p>
                    <p>Come amministratore, puoi:</p>
                    <ul>
                        <li>Aggiungere nuovi prodotti</li>
                        <li>Modificare prodotti esistenti</li>
                        <li>Eliminare prodotti</li>
                        <li>Gestire le disponibilità</li>
                    </ul>
                    <p>Per qualsiasi problema, contatta il supporto tecnico.</p>
                </div>
            </Popup>
        </main>
    );
};

export default ProductsPage;
