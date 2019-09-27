package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyAllianceFunctionBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyAllianceFunctionBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var type:int;
		public var alliance:GetAllianceFunctionResp;
		public function ReplyAllianceFunctionBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			type = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.type = this.type;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyAllianceFunctionBC
		{
			uid = undefined;
			type = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			this.type = msgObj.type;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new GetAllianceFunctionResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyAllianceFunctionBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}