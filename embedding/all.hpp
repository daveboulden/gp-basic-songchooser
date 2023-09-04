#pragma once
#include <map>
#include <tuple>
#include <string>
#include <saucer/webview.hpp>

#include "BouldenDigitalSiteIcon.png.hpp"
#include "index.html.hpp"

namespace embedded {
	inline auto get_all_files() {
		std::map<const std::string, const saucer::embedded_file> rtn;
		rtn.emplace("BouldenDigitalSiteIcon.png", saucer::embedded_file{"image/png", 29822, embedded_BouldenDigitalSiteIcon_png});
		rtn.emplace("index.html", saucer::embedded_file{"text/html", 5199, embedded_index_html});
		return rtn;
	}
} // namespace embedded