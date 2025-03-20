// src/contexts/AuthContext.tsx
import React, { createContext, useState, useContext, ReactNode } from 'react';

type UserRole = 'client' | 'admin' | null;

interface User {
  id: number;
  name: string;
  email: string;
  role: UserRole;
}

interface AuthContextType {
  user: User | null;
  isAuthenticated: boolean;
  login: (email: string, password: string) => Promise<boolean>;
  logout: () => void;
  isAdmin: () => boolean;
}

const AuthContext = createContext<AuthContextType | undefined>(undefined);

export const useAuth = () => {
  const context = useContext(AuthContext);
  if (context === undefined) {
    throw new Error('useAuth must be used within an AuthProvider');
  }
  return context;
};

interface AuthProviderProps {
  children: ReactNode;
}

export const AuthProvider: React.FC<AuthProviderProps> = ({ children }) => {
  const [user, setUser] = useState<User | null>(null);

  // Funzione di login semplificata
  const login = async (email: string, password: string): Promise<boolean> => {
    try {
      // In un'app reale, qui ci sarebbe una chiamata API
      // Per semplicità, simuliamo una risposta
      
      // Simulazione di credenziali per client e admin
      if (email === 'client@example.com' && password === 'password') {
        setUser({
          id: 1,
          name: 'Cliente Demo',
          email: 'client@example.com',
          role: 'client'
        });
        return true;
      } else if (email === 'admin@example.com' && password === 'admin') {
        setUser({
          id: 2,
          name: 'Admin Demo',
          email: 'admin@example.com',
          role: 'admin'
        });
        return true;
      }
      return false;
    } catch (error) {
      console.error('Errore durante il login:', error);
      return false;
    }
  };

  const logout = () => {
    setUser(null);
  };

  const isAdmin = () => {
    return user?.role === 'admin';
  };

  const value = {
    user,
    isAuthenticated: !!user,
    login,
    logout,
    isAdmin
  };

  return <AuthContext.Provider value={value}>{children}</AuthContext.Provider>;
};