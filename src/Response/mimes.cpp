/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mimes.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:17:23 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 16:49:23 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Config/Data/File.hpp"

void initMimes(std::map<std::string, std::string>& mimes) {
	mimes[".html"] = "text/html";
    mimes[".htm"] = "text/html";
    mimes[".css"] = "text/css";
    mimes[".js"] = "application/javascript";
    mimes[".json"] = "application/json";
    mimes[".xml"] = "application/xml";
    mimes[".png"] = "image/png";
    mimes[".jpg"] = "image/jpeg";
    mimes[".jpeg"] = "image/jpeg";
    mimes[".gif"] = "image/gif";
    mimes[".svg"] = "image/svg+xml";
    mimes[".ico"] = "image/x-icon";
    mimes[".wav"] = "audio/wav";
    mimes[".mp3"] = "audio/mpeg";
    mimes[".ogg"] = "audio/ogg";
    mimes[".mp4"] = "video/mp4";
    mimes[".mpeg"] = "video/mpeg";
    mimes[".webm"] = "video/webm";
    mimes[".pdf"] = "application/pdf";
    mimes[".zip"] = "application/zip";
    mimes[".gz"] = "application/gzip";
    mimes[".txt"] = "text/plain";
    mimes[".csv"] = "text/csv";
}

std::string getExtension(std::string name) {
	size_t ext = name.rfind('.');
	
	if (ext == std::string::npos) {
		return "";
	}
	else {
		return name.substr(ext);
	}
}

std::string getMime(std::string fileName) {
	std::map<std::string, std::string> mimes;

	initMimes(mimes);
	std::string extension = getExtension(fileName);
	std::map<std::string, std::string>::iterator it = mimes.find(extension);
	if (it != mimes.end()) {
		return it->second;
	}
	else {
		return "Content-Type: application/octet-stream";
	}
}
