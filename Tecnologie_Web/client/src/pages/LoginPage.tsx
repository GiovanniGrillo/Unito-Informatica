// src/pages/LoginPage.tsx
import React, {useState} from 'react';
import {useNavigate} from 'react-router-dom';
import LoginForm from '../components/auth/LoginForm';
import {useAuth} from '../contexts/AuthContext';

const LoginPage: React.FC = () => {
    const {login} = useAuth();
    const navigate = useNavigate();
    const [error, setError] = useState<string | null>(null);

    const handleLogin = async (email: string, password: string) => {
        try {
            const success = await login(email, password);
            if (success) {
                navigate('/');
            } else {
                setError('Credenziali non valide. Prova con client@example.com/password o admin@example.com/admin');
            }
        } catch (error) {
            setError('Si è verificato un errore durante il login.');
            console.error('Errore:', error);
        }
    };

    return (
        <div>
            {error && <div className="error-message">{error}</div>}
            <LoginForm onLogin={handleLogin}/>
        </div>

    );
};

export default LoginPage;