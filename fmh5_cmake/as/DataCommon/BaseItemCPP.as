package com.sanguo.game.server.connectlogic.common.message.DataCommon
{
	import laya.utils.Byte;
	public class BaseItemCPP
	{
		public static const PROTO:String = "DataCommon.BaseItemCPP";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public var change:int;
		public var totalValue:Number;
		public function BaseItemCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
			change = undefined;
			totalValue = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			serializeObj.change = this.change;
			serializeObj.totalValue = this.totalValue;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BaseItemCPP
		{
			type = undefined;
			change = undefined;
			totalValue = undefined;
			this.type = msgObj.type;
			this.change = msgObj.change;
			this.totalValue = msgObj.totalValue;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BaseItemCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}