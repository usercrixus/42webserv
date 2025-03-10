#config file:  

"host"	Defines the IP address or hostname where the server will listen.  
"port"	Port number where the server will run.  
"server_names"	List of domain names that this server responds to (for virtual hosting).  
"error_pages"	Maps HTTP error codes (e.g., 404, 500) to specific HTML error pages.  
"client_max_body_size"	Sets the maximum size (in bytes) for client request bodies.  
"routes"	Contains detailed route configurations.  
"path"	Defines the URL path for this route.  
"accepted_methods"	List of HTTP methods allowed for this route.  
"root"	Defines the directory to serve content from.  
"index"	Sets the default file for directory requests.  
"directory_listing"	Enables or disables directory listing (if no index is found).  
"upload_directory"	Specifies where uploaded files should be stored.  
"max_upload_size"	Sets a limit for individual uploaded file sizes.  
"redirect"	Defines a URL for HTTP redirection.  
"cgi_enabled"	Enables CGI execution on this route.  
"cgi_extensions"	List of file extensions that trigger CGI (e.g., .py, .php).  
"cgi_root"	The root folder where CGI scripts are located.  