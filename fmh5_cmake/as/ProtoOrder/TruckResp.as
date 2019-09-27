package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class TruckResp
	{
		public static const PROTO:String = "ProtoOrder.TruckResp";
		public var package_root:*;
		public  var message:*;
		public var truck:TruckCPP;
		public function TruckResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			truck = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.truck = this.truck.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):TruckResp
		{
			truck = undefined;
			this.truck = new TruckCPP(package_root).unserialize(msgObj.truck);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):TruckResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}