// client/src/pages/ProductsPage.tsx
import React, {useState, useEffect} from 'react';
import ProductGrid from '../components/features/ProductGrid';
import ProductFilter from '../components/features/ProductFilter';
import Popup from '../components/features/Popup';
import AddProductForm from '../components/features/AddProductForm';
import {useCart} from '../contexts/CartContext';
import {useAuth} from '../contexts/AuthContext';
import '../styles/product-grid.css';
import '../styles/filter.css';
import '../styles/popup.css';
import '../styles/products-actions.css';
import '../styles/form-buttons.css';

import { Product } from '../types/Product';

const ProductsPage: React.FC = () => {
    const [products, setProducts] = useState<Product[]>([]);
    const [filteredProducts, setFilteredProducts] = useState<Product[]>([]);
    const [categories, setCategories] = useState<string[]>([]);
    const [selectedCategory, setSelectedCategory] = useState<string | null>(null);
    const [loading, setLoading] = useState<boolean>(true);
    const [error, setError] = useState<string | null>(null);
    const [showAddModal, setShowAddModal] = useState<boolean>(false);
    const [showEditModal, setShowEditModal] = useState<boolean>(false);
    const [showInfoModal, setShowInfoModal] = useState<boolean>(false);
    const [newProduct, setNewProduct] = useState<Partial<Product>>({});
    const [editingProduct, setEditingProduct] = useState<Product | null>(null);
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
    const handleAddProduct = async (product: Omit<Product, 'id'>) => {
        try {
            const response = await fetch('http://localhost:8080/products', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(product),
            });

            if (response.ok) {
                // Aggiorna la lista dei prodotti dopo l'aggiunta
                const updatedProduct = await response.json();
                setProducts(prevProducts => [...prevProducts, updatedProduct]);
                setFilteredProducts(prevProducts => [...prevProducts, updatedProduct]);
                setShowAddModal(false);
                setNewProduct({});
            } else {
                console.error('Errore durante l\'aggiunta del prodotto');
            }
        } catch (error) {
            console.error('Errore:', error);
        }
    };
    
    // Funzione per modificare un prodotto esistente
    const handleEditProduct = async (product: Product) => {
        setEditingProduct(product);
        setShowEditModal(true);
    };
    
    // Funzione per salvare le modifiche a un prodotto
    const handleUpdateProduct = async (updatedProduct: Omit<Product, 'id'>) => {
        if (!editingProduct) return;
        
        try {
            const response = await fetch(`http://localhost:8080/products/${editingProduct.id}`, {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({...updatedProduct, id: editingProduct.id}),
            });

            if (response.ok) {
                const updated = await response.json();
                // Aggiorna la lista dei prodotti dopo la modifica
                setProducts(prevProducts => 
                    prevProducts.map(p => p.id === updated.id ? updated : p)
                );
                setFilteredProducts(prevProducts => 
                    prevProducts.map(p => p.id === updated.id ? updated : p)
                );
                setShowEditModal(false);
                setEditingProduct(null);
            } else {
                console.error('Errore durante l\'aggiornamento del prodotto');
            }
        } catch (error) {
            console.error('Errore:', error);
        }
    };
    
    // Funzione per eliminare un prodotto
    const handleDeleteProduct = async (product: Product) => {
        if (window.confirm(`Sei sicuro di voler eliminare il prodotto "${product.name}"?`)) {
            try {
                const response = await fetch(`http://localhost:8080/products/${product.id}`, {
                    method: 'DELETE',
                });

                if (response.ok) {
                    // Rimuovi il prodotto dalla lista
                    setProducts(prevProducts => 
                        prevProducts.filter(p => p.id !== product.id)
                    );
                    setFilteredProducts(prevProducts => 
                        prevProducts.filter(p => p.id !== product.id)
                    );
                } else {
                    console.error('Errore durante l\'eliminazione del prodotto');
                }
            } catch (error) {
                console.error('Errore:', error);
            }
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
                                className="button button-info" 
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
                                onEditProduct={handleEditProduct}
                                onDeleteProduct={handleDeleteProduct}
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
            >
                <AddProductForm 
                    categories={categories}
                    onSubmit={handleAddProduct}
                    onCancel={() => setShowAddModal(false)}
                />
            </Popup>
            
            {/* Modale per modificare un prodotto esistente */}
            <Popup 
                isOpen={showEditModal} 
                onClose={() => {
                    setShowEditModal(false);
                    setEditingProduct(null);
                }} 
                title="Modifica Prodotto"
            >
                {editingProduct && (
                    <AddProductForm 
                        categories={categories}
                        onSubmit={handleUpdateProduct}
                        onCancel={() => {
                            setShowEditModal(false);
                            setEditingProduct(null);
                        }}
                        initialData={{
                            name: editingProduct.name,
                            category: editingProduct.category,
                            price: editingProduct.price,
                            description: editingProduct.description,
                            imageUrl: editingProduct.imageUrl,
                            availableQuantity: editingProduct.availableQuantity || 0
                        }}
                    />
                )}
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
