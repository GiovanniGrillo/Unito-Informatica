import React from 'react';
import { Link } from 'react-router-dom';
import '../styles/not-found.css';

const NotFoundPage: React.FC = () => {
  return (
    <div className="not-found-container">
      <h1>404</h1>
      <h2>Pagina Non Trovata</h2>
      <p>La pagina che stai cercando non esiste o è stata spostata.</p>
      <Link to="/" className="btn btn-primary">
        Torna alla Home
      </Link>
    </div>
  );
};

export default NotFoundPage;