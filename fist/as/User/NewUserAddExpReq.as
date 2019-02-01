package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class NewUserAddExpReq
	{
		public static const PROTO:String = "User.NewUserAddExpReq";
		public var package_root:*;
		public  var message:*;
		public var exp:int;
		public function NewUserAddExpReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			exp = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.exp = this.exp;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NewUserAddExpReq
		{
			exp = undefined;
			this.exp = msgObj.exp;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NewUserAddExpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}