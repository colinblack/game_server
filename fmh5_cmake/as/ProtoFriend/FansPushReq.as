package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class FansPushReq
	{
		public static const PROTO:String = "ProtoFriend.FansPushReq";
		public var package_root:*;
		public  var message:*;
		public var fan:FansCPP;
		public function FansPushReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			fan = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.fan = this.fan.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):FansPushReq
		{
			fan = undefined;
			this.fan = new FansCPP(package_root).unserialize(msgObj.fan);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FansPushReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}