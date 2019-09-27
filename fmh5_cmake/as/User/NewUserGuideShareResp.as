package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class NewUserGuideShareResp
	{
		public static const PROTO:String = "User.NewUserGuideShareResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function NewUserGuideShareResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):NewUserGuideShareResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NewUserGuideShareResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}