<?php
// Récupérer la valeur de "name" depuis QUERY_STRING (via $_GET)
$name = isset($_GET['name']) ? $_GET['name'] : "Inconnu";

// Générer une page HTML simple
echo "<!DOCTYPE html>\n";
echo "<html lang=\"en\">\n";
echo "<head>\n";
echo "    <meta charset=\"UTF-8\">\n";
echo "    <title>CGI1</title>\n";
echo "</head>\n";
echo "<body>\n";
echo "    <h1>Bonjour, " . htmlspecialchars($name) . " !</h1>\n";
echo "    <p>La QUERY_STRING reçue est : " . htmlspecialchars($_SERVER['QUERY_STRING']) . "</p>\n";

echo "    <h2>Variables d'environnement :</h2>\n";
echo "    <ul>\n";
echo "        <li>REQUEST_METHOD: " . htmlspecialchars($_SERVER['REQUEST_METHOD']) . "</li>\n";
echo "        <li>SCRIPT_FILENAME: " . htmlspecialchars($_SERVER['SCRIPT_FILENAME']) . "</li>\n";
echo "        <li>PATH_INFO: " . htmlspecialchars($_SERVER['PATH_INFO'] ?? 'Non défini') . "</li>\n";
echo "        <li>QUERY_STRING: " . htmlspecialchars($_SERVER['QUERY_STRING']) . "</li>\n";
echo "    </ul>\n";

echo "</body>\n";
echo "</html>\n";
?>
