package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class PushFullBoxShipMsg
	{
		public static const PROTO:String = "ProtoShipping.PushFullBoxShipMsg";
		public var package_root:*;
		public  var message:*;
		public var point:FullBoxShipCPP;
		public function PushFullBoxShipMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			point = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.point = this.point.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushFullBoxShipMsg
		{
			point = undefined;
			this.point = new FullBoxShipCPP(package_root).unserialize(msgObj.point);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushFullBoxShipMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}