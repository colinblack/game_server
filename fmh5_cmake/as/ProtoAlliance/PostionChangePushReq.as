package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class PostionChangePushReq
	{
		public static const PROTO:String = "ProtoAlliance.PostionChangePushReq";
		public var package_root:*;
		public  var message:*;
		public var oldpos:int;
		public var newpos:int;
		public var alliance:AllianceCPP;
		public function PostionChangePushReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			oldpos = undefined;
			newpos = undefined;
			alliance = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.oldpos = this.oldpos;
			serializeObj.newpos = this.newpos;
			if(this.alliance!= undefined)
			{
				serializeObj.alliance = this.alliance.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PostionChangePushReq
		{
			oldpos = undefined;
			newpos = undefined;
			alliance = undefined;
			this.oldpos = msgObj.oldpos;
			this.newpos = msgObj.newpos;
			if(msgObj.hasOwnProperty("alliance"))
			{
				this.alliance = new AllianceCPP(package_root).unserialize(msgObj.alliance);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PostionChangePushReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}