package com.sanguo.game.server.connectlogic.common.message.DataCommon
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BaseItemCPP
	{
		public static const PROTO:String = "DataCommon.BaseItemCPP";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public var change:int;
		public var totalValue:Number;
		public var powerTs:int;
		public var OnhookCoinTs:int;
		public var OnhookExpTs:int;
		public function BaseItemCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			type = undefined;
			change = undefined;
			totalValue = undefined;
			powerTs = undefined;
			OnhookCoinTs = undefined;
			OnhookExpTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			serializeObj.change = this.change;
			serializeObj.totalValue = this.totalValue;
			if(this.powerTs!= undefined)
			{
				serializeObj.powerTs = this.powerTs;
			}
			if(this.OnhookCoinTs!= undefined)
			{
				serializeObj.OnhookCoinTs = this.OnhookCoinTs;
			}
			if(this.OnhookExpTs!= undefined)
			{
				serializeObj.OnhookExpTs = this.OnhookExpTs;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):BaseItemCPP
		{
			type = undefined;
			change = undefined;
			totalValue = undefined;
			powerTs = undefined;
			OnhookCoinTs = undefined;
			OnhookExpTs = undefined;
			this.type = msgObj.type;
			this.change = msgObj.change;
			this.totalValue = msgObj.totalValue;
			if(msgObj.hasOwnProperty("powerTs"))
			{
				this.powerTs = msgObj.powerTs;
			}
			if(msgObj.hasOwnProperty("OnhookCoinTs"))
			{
				this.OnhookCoinTs = msgObj.OnhookCoinTs;
			}
			if(msgObj.hasOwnProperty("OnhookExpTs"))
			{
				this.OnhookExpTs = msgObj.OnhookExpTs;
			}
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