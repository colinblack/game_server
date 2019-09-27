package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class FetchSelfResp
	{
		public static const PROTO:String = "User.FetchSelfResp";
		public var package_root:*;
		public  var message:*;
		public var player:User;
		public function FetchSelfResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			player = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.player = this.player.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchSelfResp
		{
			player = undefined;
			this.player = new User(package_root).unserialize(msgObj.player);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchSelfResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}