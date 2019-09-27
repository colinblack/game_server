package com.sanguo.game.server.connectlogic.common.message.ProtoMessageBoard
{
	import laya.utils.Byte;
	public class GetFeedbackResp
	{
		public static const PROTO:String = "ProtoMessageBoard.GetFeedbackResp";
		public var package_root:*;
		public  var message:*;
		public var restTimes:int;
		public var arrayFeedback:Vector.<FeedbackInfo>;
		public function GetFeedbackResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			restTimes = undefined;
			arrayFeedback = new Vector.<FeedbackInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.restTimes = this.restTimes;
			serializeObj.arrayFeedback = [];
			for(var i:int = 0;i < this.arrayFeedback.length;i++)
			{
				serializeObj.arrayFeedback.push(this.arrayFeedback[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFeedbackResp
		{
			restTimes = undefined;
			arrayFeedback = new Vector.<FeedbackInfo>();
			this.restTimes = msgObj.restTimes;
			for(var i:int = 0;i < msgObj.arrayFeedback.length;i++)
			{
				this.arrayFeedback.push(new FeedbackInfo(package_root).unserialize(msgObj.arrayFeedback[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFeedbackResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}