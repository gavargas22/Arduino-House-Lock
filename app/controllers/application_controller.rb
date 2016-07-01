class ApplicationController < ActionController::Base
	include SessionsHelper
	# Prevent CSRF attacks by raising an exception.
	# For APIs, you may want to use :null_session instead.
	protect_from_forgery with: :exception


	private
		# Redirects to login page if a user has not logged in
		def logged_in_user
			unless logged_in?
				redirect_to login_path
			end
		end
		# Redirect to the root if the current user is not admin
		def admin_user
			redirect_to(root_url) unless current_user.admin?
		end
		# Redirect to the error no access page if the user has no door access
		def has_door_access
			redirect_to(no_access_path) unless current_user.access?
		end
end
