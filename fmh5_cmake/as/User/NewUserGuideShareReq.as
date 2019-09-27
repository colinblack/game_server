package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class NewUserGuideShareReq
	{
		public static const PROTO:String = "User.NewUserGuideShareReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var type:int;
		public function NewUserGuideShareReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NewUserGuideShareReq
		{
			id = undefined;
			type = undefined;
			this.id = msgObj.id;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NewUserGuideShareReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}