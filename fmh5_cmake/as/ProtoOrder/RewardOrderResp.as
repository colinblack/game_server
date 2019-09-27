package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class RewardOrderResp
	{
		public static const PROTO:String = "ProtoOrder.RewardOrderResp";
		public var package_root:*;
		public  var message:*;
		public var result:Boolean;
		public var commons:CommonItemsCPP;
		public var truck:TruckCPP;
		public function RewardOrderResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			result = undefined;
			commons = undefined;
			truck = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.result = this.result;
			serializeObj.commons = this.commons.serialize();
			serializeObj.truck = this.truck.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardOrderResp
		{
			result = undefined;
			commons = undefined;
			truck = undefined;
			this.result = msgObj.result;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.truck = new TruckCPP(package_root).unserialize(msgObj.truck);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardOrderResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}