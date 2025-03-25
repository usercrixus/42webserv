<?php
// Récupérer les données envoyées via POST (depuis php://input ou $_POST)
$input = file_get_contents("php://input"); // Lit le corps brut de la requête POST
parse_str($input, $params); // Convertit les données POST (ex. "name=Jean&age=25") en tableau
$name = isset($params['name']) ? $params['name'] : "Inconnu";
$age = isset($params['age']) ? $params['age'] : "Non spécifié";

// Générer une page HTML simple
echo "<!DOCTYPE html>\n";
echo "<html lang=\"en\">\n";
echo "<head>\n";
echo "    <meta charset=\"UTF-8\">\n";
echo "    <title>CGI POST Test</title>\n";
echo "</head>\n";
echo "<body>\n";
echo "    <h1>Bonjour, " . htmlspecialchars($name) . " !</h1>\n";
echo "    <p>Votre âge est : " . htmlspecialchars($age) . "</p>\n";
echo "    <p>Données brutes reçues via POST : " . htmlspecialchars($input) . "</p>\n";

echo "    <h2>Variables d'environnement :</h2>\n";
echo "    <ul>\n";
echo "        <li>REQUEST_METHOD: " . htmlspecialchars($_SERVER['REQUEST_METHOD']) . "</li>\n";
echo "        <li>SCRIPT_FILENAME: " . htmlspecialchars($_SERVER['SCRIPT_FILENAME']) . "</li>\n";
echo "        <li>CONTENT_LENGTH: " . htmlspecialchars($_SERVER['CONTENT_LENGTH'] ?? 'Non défini') . "</li>\n";
echo "        <li>CONTENT_TYPE: " . htmlspecialchars($_SERVER['CONTENT_TYPE'] ?? 'Non défini') . "</li>\n";
echo "    </ul>\n";

echo "</body>\n";
echo "</html>\n";
?>