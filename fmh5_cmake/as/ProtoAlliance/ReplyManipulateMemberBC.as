package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ReplyManipulateMemberBC
	{
		public static const PROTO:String = "ProtoAlliance.ReplyManipulateMemberBC";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var alliance:ManipulateMemberResp;
		public function ReplyManipulateMemberBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ReplyManipulateMemberBC
		{
			uid = undefined;
			alliance = undefined;
			this.uid = msgObj.uid;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new ManipulateMemberResp(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ReplyManipulateMemberBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}