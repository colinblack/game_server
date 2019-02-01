package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class OtherUser
	{
		public static const PROTO:String = "User.OtherUser";
		public var package_root:*;
		public  var message:*;
		public var base:Base;
		public function OtherUser(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			base = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.base = this.base.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):OtherUser
		{
			base = undefined;
			this.base = new Base(package_root).unserialize(msgObj.base);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OtherUser
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}