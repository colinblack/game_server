package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class FansCPP
	{
		public static const PROTO:String = "ProtoFriend.FansCPP";
		public var package_root:*;
		public  var message:*;
		public var fan:FolkCPP;
		public function FansCPP(root:*)
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
		public function unserialize(msgObj:*):FansCPP
		{
			fan = undefined;
			this.fan = new FolkCPP(package_root).unserialize(msgObj.fan);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FansCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}