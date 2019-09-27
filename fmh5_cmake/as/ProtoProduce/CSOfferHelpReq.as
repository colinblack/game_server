package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class CSOfferHelpReq
	{
		public static const PROTO:String = "ProtoProduce.CSOfferHelpReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var othuid:int;
		public var treeud:int;
		public var allianceid:int;
		public function CSOfferHelpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			othuid = undefined;
			treeud = undefined;
			allianceid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = this.othuid;
			serializeObj.treeud = this.treeud;
			if(this.allianceid!= undefined)
			{
				serializeObj.allianceid = this.allianceid;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSOfferHelpReq
		{
			myuid = undefined;
			othuid = undefined;
			treeud = undefined;
			allianceid = undefined;
			this.myuid = msgObj.myuid;
			this.othuid = msgObj.othuid;
			this.treeud = msgObj.treeud;
			if(msgObj.hasOwnProperty("allianceid"))
			{
				this.allianceid = msgObj.allianceid;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSOfferHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}