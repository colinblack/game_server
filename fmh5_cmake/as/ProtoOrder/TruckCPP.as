package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class TruckCPP
	{
		public static const PROTO:String = "ProtoOrder.TruckCPP";
		public var package_root:*;
		public  var message:*;
		public var state:int;
		public var end_ts:int;
		public var coin:int;
		public var exp:int;
		public function TruckCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			state = undefined;
			end_ts = undefined;
			coin = undefined;
			exp = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.state = this.state;
			serializeObj.end_ts = this.end_ts;
			serializeObj.coin = this.coin;
			serializeObj.exp = this.exp;
			return serializeObj;
		}
		public function unserialize(msgObj:*):TruckCPP
		{
			state = undefined;
			end_ts = undefined;
			coin = undefined;
			exp = undefined;
			this.state = msgObj.state;
			this.end_ts = msgObj.end_ts;
			this.coin = msgObj.coin;
			this.exp = msgObj.exp;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):TruckCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}