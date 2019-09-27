package com.sanguo.game.server.connectlogic.common.message.ProtoNPCCustomer
{
	import laya.utils.Byte;
	public class GetNPCCustomerResp
	{
		public static const PROTO:String = "ProtoNPCCustomer.GetNPCCustomerResp";
		public var package_root:*;
		public  var message:*;
		public var customer:Vector.<NPCCustomerCPP>;
		public function GetNPCCustomerResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			customer = new Vector.<NPCCustomerCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.customer = [];
			for(var i:int = 0;i < this.customer.length;i++)
			{
				serializeObj.customer.push(this.customer[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNPCCustomerResp
		{
			customer = new Vector.<NPCCustomerCPP>();
			for(var i:int = 0;i < msgObj.customer.length;i++)
			{
				this.customer.push(new NPCCustomerCPP(package_root).unserialize(msgObj.customer[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNPCCustomerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}