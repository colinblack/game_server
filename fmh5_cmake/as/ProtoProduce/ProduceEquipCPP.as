package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ProduceEquipCPP
	{
		public static const PROTO:String = "ProtoProduce.ProduceEquipCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var status:int;
		public var queuenum:int;
		public var queuedata:Vector.<int>;
		public var shelfdata:Vector.<int>;
		public var finishtime:int;
		public var shelfsource:Vector.<int>;
		public var keeper:int;
		public function ProduceEquipCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			status = undefined;
			queuenum = undefined;
			queuedata = new Vector.<int>();
			shelfdata = new Vector.<int>();
			finishtime = undefined;
			shelfsource = new Vector.<int>();
			keeper = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.status = this.status;
			serializeObj.queuenum = this.queuenum;
			serializeObj.queuedata = [];
			for(var i:int = 0;i < this.queuedata.length;i++)
			{
				serializeObj.queuedata.push(this.queuedata[i]);
			}
			serializeObj.shelfdata = [];
			for(var i:int = 0;i < this.shelfdata.length;i++)
			{
				serializeObj.shelfdata.push(this.shelfdata[i]);
			}
			serializeObj.finishtime = this.finishtime;
			serializeObj.shelfsource = [];
			for(var i:int = 0;i < this.shelfsource.length;i++)
			{
				serializeObj.shelfsource.push(this.shelfsource[i]);
			}
			if(this.keeper!= undefined)
			{
				serializeObj.keeper = this.keeper;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProduceEquipCPP
		{
			ud = undefined;
			status = undefined;
			queuenum = undefined;
			queuedata = new Vector.<int>();
			shelfdata = new Vector.<int>();
			finishtime = undefined;
			shelfsource = new Vector.<int>();
			keeper = undefined;
			this.ud = msgObj.ud;
			this.status = msgObj.status;
			this.queuenum = msgObj.queuenum;
			for(var i:int = 0;i < msgObj.queuedata.length;i++)
			{
				this.queuedata.push(msgObj.queuedata[i]);
			}
			for(var i:int = 0;i < msgObj.shelfdata.length;i++)
			{
				this.shelfdata.push(msgObj.shelfdata[i]);
			}
			this.finishtime = msgObj.finishtime;
			for(var i:int = 0;i < msgObj.shelfsource.length;i++)
			{
				this.shelfsource.push(msgObj.shelfsource[i]);
			}
			if(msgObj.hasOwnProperty("keeper"))
			{
				this.keeper = msgObj.keeper;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProduceEquipCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}