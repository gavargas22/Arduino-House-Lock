class SessionsController < ApplicationController
	include SessionsHelper
	# Redirect to SSO Page and link a call_back to create a session
	def new
		cookies[:referrer] = request.referrer
		redirect_to "https://adminapps.utep.edu/sso?redirectURL=#{create_session_url}"
	end

	# Create a new session using UTEPSSO
	def create
		user = User.from_sso(cookies[:UTEP_SE], cookies[:UTEP_SA])
		log_in(user) if user
		redirect_url = cookies.fetch(:referrer) {root_url}
		redirect_to redirect_url
	end

	# Terminate current session and deauthenticate from SSO system
	def destroy
		log_out
		UTEPSSO.deauthenticate(cookies[:UTEP_SE], cookies[:UTEP_SA])
		redirect_to root_url
	end
end
