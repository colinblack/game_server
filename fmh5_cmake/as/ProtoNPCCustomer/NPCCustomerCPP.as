package com.sanguo.game.server.connectlogic.common.message.ProtoNPCCustomer
{
	import laya.utils.Byte;
	public class NPCCustomerCPP
	{
		public static const PROTO:String = "ProtoNPCCustomer.NPCCustomerCPP";
		public var package_root:*;
		public  var message:*;
		public var propsId:int;
		public var propsCnt:int;
		public var nextts:int;
		public function NPCCustomerCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsId = undefined;
			propsCnt = undefined;
			nextts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.propsId!= undefined)
			{
				serializeObj.propsId = this.propsId;
			}
			if(this.propsCnt!= undefined)
			{
				serializeObj.propsCnt = this.propsCnt;
			}
			serializeObj.nextts = this.nextts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NPCCustomerCPP
		{
			propsId = undefined;
			propsCnt = undefined;
			nextts = undefined;
			if(msgObj.hasOwnProperty("propsId"))
			{
				this.propsId = msgObj.propsId;
			}
			if(msgObj.hasOwnProperty("propsCnt"))
			{
				this.propsCnt = msgObj.propsCnt;
			}
			this.nextts = msgObj.nextts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NPCCustomerCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}