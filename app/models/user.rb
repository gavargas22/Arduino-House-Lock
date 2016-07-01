require 'utep_sso'

class User < ActiveRecord::Base
	# Return a User with SSO information
	def self.from_sso(utep_cookie, utep_salt)
		sso_response = UTEPSSO.authenticate(utep_cookie, utep_salt)
		user = User.find_or_initialize_by(username: sso_response[:user_name])
		# User exists already
		return user unless user.id.nil?

		user.name = sso_response[:full_name]
		user.username = sso_response[:user_name]
		# user.slug = sso_response[:user_name]
		user.email = sso_response[:email_address]
		user.created_at = Time.now
		user.save!
	end
end
